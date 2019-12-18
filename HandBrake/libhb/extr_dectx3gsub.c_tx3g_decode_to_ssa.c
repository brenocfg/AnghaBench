#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_14__ {int line; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_13__ {int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  frametype; } ;
struct TYPE_15__ {char* data; int size; TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;
struct TYPE_16__ {int startChar; int endChar; void* textColorRGBA; void* fontSize; void* faceStyleFlags; void* fontID; } ;
typedef  TYPE_4__ StyleRecord ;

/* Variables and functions */
 int FOURCC (char*) ; 
 int /*<<< orphan*/  HB_FRAME_SUBTITLE ; 
 scalar_t__ IS_10xxxxxx (char) ; 
 int MAX_MARKUP_LEN ; 
 char* READ_ARRAY (int) ; 
 void* READ_U16 () ; 
 void* READ_U32 () ; 
 void* READ_U8 () ; 
 int /*<<< orphan*/  SKIP_ARRAY (int) ; 
 int SSA_PREAMBLE_LEN ; 
 int /*<<< orphan*/  WRITE_CHAR (char) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_3__**) ; 
 TYPE_3__* hb_buffer_init (int) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  write_ssa_markup (char*,TYPE_4__*) ; 

__attribute__((used)) static hb_buffer_t *tx3g_decode_to_ssa(hb_work_private_t *pv, hb_buffer_t *in)
{
    uint8_t *pos = in->data;
    uint8_t *end = in->data + in->size;

    uint16_t numStyleRecords = 0;
    StyleRecord *styleRecords = NULL;

    /*
     * Parse the packet as a TX3G TextSample.
     *
     * Look for a single StyleBox ('styl') and read all contained StyleRecords.
     * Ignore all other box types.
     *
     * NOTE: Buffer overflows on read are not checked.
     */
    uint16_t textLength = READ_U16();
    uint8_t *text = READ_ARRAY(textLength);
    while ( pos < end )
    {
        /*
         * Read TextSampleModifierBox
         */
        uint32_t size = READ_U32();
        if ( size == 0 )
        {
            size = pos - end;   // extends to end of packet
        }
        if ( size == 1 )
        {
            hb_log( "dectx3gsub: TextSampleModifierBox has unsupported large size" );
            break;
        }
        uint32_t type = READ_U32();
        if (type == FOURCC("uuid"))
        {
            hb_log( "dectx3gsub: TextSampleModifierBox has unsupported extended type" );
            break;
        }

        if (type == FOURCC("styl"))
        {
            // Found a StyleBox. Parse the contained StyleRecords

            if ( numStyleRecords != 0 )
            {
                hb_log( "dectx3gsub: found additional StyleBoxes on subtitle; skipping" );
                SKIP_ARRAY(size);
                continue;
            }

            numStyleRecords = READ_U16();
            if (numStyleRecords > 0)
                styleRecords = calloc(numStyleRecords, sizeof(StyleRecord));

            int i;
            for (i = 0; i < numStyleRecords; i++)
            {
                styleRecords[i].startChar         = READ_U16();
                styleRecords[i].endChar           = READ_U16();
                styleRecords[i].fontID            = READ_U16();
                styleRecords[i].faceStyleFlags    = READ_U8();
                styleRecords[i].fontSize          = READ_U8();
                styleRecords[i].textColorRGBA     = READ_U32();
            }
        }
        else
        {
            // Found some other kind of TextSampleModifierBox. Skip it.
            SKIP_ARRAY(size);
        }
    }

    /*
     * Copy text to output buffer, and add HTML markup for the style records
     */
    int maxOutputSize = textLength + SSA_PREAMBLE_LEN + (numStyleRecords * MAX_MARKUP_LEN);
    hb_buffer_t *out = hb_buffer_init( maxOutputSize );
    if ( out == NULL )
        goto fail;
    uint8_t *dst = out->data;
    uint8_t *start;
    int charIndex = 0;
    int styleIndex = 0;

    sprintf((char*)dst, "%d,,Default,,0,0,0,,", pv->line);
    dst += strlen((char*)dst);
    start = dst;
    for (pos = text, end = text + textLength; pos < end; pos++)
    {
        if (IS_10xxxxxx(*pos))
        {
            // Is a non-first byte of a multi-byte UTF-8 character
            WRITE_CHAR(*pos);
            continue;   // ...without incrementing 'charIndex'
        }

        if (styleIndex < numStyleRecords)
        {
            if (styleRecords[styleIndex].endChar == charIndex)
            {
                if (styleIndex + 1 >= numStyleRecords ||
                    styleRecords[styleIndex+1].startChar > charIndex)
                {
                    dst += write_ssa_markup((char*)dst, NULL);
                }
                styleIndex++;
            }
            if (styleRecords[styleIndex].startChar == charIndex)
            {
                dst += write_ssa_markup((char*)dst, &styleRecords[styleIndex]);
            }
        }

        if (*pos == '\n')
        {
            WRITE_CHAR('\\');
            WRITE_CHAR('N');
        }
        else
        {
            WRITE_CHAR(*pos);
        }
        charIndex++;
    }
    if (start == dst)
    {
        // No text in the subtitle.  This sub is just filler, drop it.
        free(styleRecords);
        hb_buffer_close(&out);
        return NULL;
    }
    *dst = '\0';
    dst++;

    // Trim output buffer to the actual amount of data written
    out->size = dst - out->data;

    // Copy metadata from the input packet to the output packet
    out->s.frametype    = HB_FRAME_SUBTITLE;
    out->s.start        = in->s.start;
    out->s.stop         = in->s.stop;
    out->s.scr_sequence = in->s.scr_sequence;

fail:
    free(styleRecords);

    return out;
}