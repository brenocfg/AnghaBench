#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_PEER_CODEC ;
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int) ; 
 int /*<<< orphan*/  BTA_AG_CODEC_CVSD ; 
 int /*<<< orphan*/  BTA_AG_CODEC_MSBC ; 
 int /*<<< orphan*/  BTA_AG_CODEC_NONE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
#define  UUID_CODEC_CVSD 129 
#define  UUID_CODEC_MSBC 128 
 int utl_str2int (char*) ; 

__attribute__((used)) static tBTA_AG_PEER_CODEC bta_ag_parse_bac(tBTA_AG_SCB *p_scb, char *p_s)
{
    tBTA_AG_PEER_CODEC  retval = BTA_AG_CODEC_NONE;
    UINT16  uuid_codec;
    BOOLEAN cont = FALSE;       /* Continue processing */
    char *p;

    while (p_s) {
        /* skip to comma delimiter */
        for (p = p_s; *p != ',' && *p != 0; p++);

        /* get integre value */
        if (*p != 0) {
            *p = 0;
            cont = TRUE;
        } else {
            cont = FALSE;
        }
        uuid_codec = utl_str2int(p_s);
        switch(uuid_codec) {
            case UUID_CODEC_CVSD:   
                retval |= BTA_AG_CODEC_CVSD;     
                break;
            
            case UUID_CODEC_MSBC:   
                retval |= BTA_AG_CODEC_MSBC;     
                break;
            
            default:
                APPL_TRACE_ERROR("Unknown Codec UUID(%d) received", uuid_codec);
                return BTA_AG_CODEC_NONE;
        }
        if (cont) {
            p_s = p + 1;
        }
        else {
            break;
        }
    }
    return (retval);
}