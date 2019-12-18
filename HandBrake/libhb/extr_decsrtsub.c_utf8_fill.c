#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {char* utf8_buf; size_t utf8_pos; size_t utf8_end; int end; int pos; char* buf; int utf8_bom_skipped; int /*<<< orphan*/  file; int /*<<< orphan*/  iconv_context; } ;
typedef  TYPE_1__ hb_work_private_t ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 size_t iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

__attribute__((used)) static int utf8_fill( hb_work_private_t * pv )
{
    int bytes, conversion = 0;
    size_t out_size;

    /* Align utf8 data to beginning of the buffer so that we can
     * fill the buffer to its maximum */
    memmove( pv->utf8_buf, pv->utf8_buf + pv->utf8_pos, pv->utf8_end - pv->utf8_pos );
    pv->utf8_end -= pv->utf8_pos;
    pv->utf8_pos = 0;
    out_size = 2048 - pv->utf8_end;
    while( out_size )
    {
        char *p, *q;
        size_t in_size, retval;

        if( pv->end == pv->pos )
        {
            bytes = fread( pv->buf, 1, 1024, pv->file );
            pv->pos = 0;
            pv->end = bytes;
            if( bytes == 0 )
            {
                return conversion;
            }
        }

        p = pv->buf + pv->pos;
        q = pv->utf8_buf + pv->utf8_end;
        in_size = pv->end - pv->pos;

        retval = iconv( pv->iconv_context, &p, &in_size, &q, &out_size);
        if (q != pv->utf8_buf + pv->utf8_end)
        {
            conversion = 1;
        }

        pv->utf8_end = q - pv->utf8_buf;
        pv->pos = p - pv->buf;

        if ( !pv->utf8_bom_skipped )
        {
            uint8_t *buf = (uint8_t*)pv->utf8_buf;
            if (buf[0] == 0xef && buf[1] == 0xbb && buf[2] == 0xbf)
            {
                pv->utf8_pos = 3;
                if (pv->utf8_pos == pv->utf8_end)
                {
                    // If only the bom was converted, indicate no conversion
                    conversion = 0;
                }
            }
            pv->utf8_bom_skipped = 1;
        }

        if( ( retval == -1 ) && ( errno == EINVAL ) )
        {
            /* Incomplete multibyte sequence, read more data */
            memmove( pv->buf, p, pv->end - pv->pos );
            pv->end -= pv->pos;
            pv->pos = 0;
            bytes = fread( pv->buf + pv->end, 1, 1024 - pv->end, pv->file );
            if( bytes == 0 )
            {
                return conversion;
            }
            pv->end += bytes;
        } else if ( ( retval == -1 ) && ( errno == EILSEQ ) )
        {
            hb_error( "Invalid byte for codeset in input, discard byte" );
            /* Try the next byte of the input */
            pv->pos++;
        } else if ( ( retval == -1 ) && ( errno == E2BIG ) )
        {
            /* buffer full */
            return conversion;
        }
    }
    return 1;
}