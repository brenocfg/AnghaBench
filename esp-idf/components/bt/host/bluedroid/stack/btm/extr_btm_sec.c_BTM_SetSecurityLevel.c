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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ CONNECTION_TYPE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ CONN_ORIENT_ORIG ; 
 scalar_t__ CONN_ORIENT_TERM ; 
 scalar_t__ btm_sec_set_security_level (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_SetSecurityLevel (BOOLEAN is_originator, const char *p_name, UINT8 service_id,
                              UINT16 sec_level, UINT16 psm, UINT32 mx_proto_id,
                              UINT32 mx_chan_id)
{
#if (L2CAP_UCD_INCLUDED == TRUE)
    CONNECTION_TYPE conn_type;

    if (is_originator) {
        conn_type = CONN_ORIENT_ORIG;
    } else {
        conn_type = CONN_ORIENT_TERM;
    }

    return (btm_sec_set_security_level (conn_type, p_name, service_id,
                                        sec_level, psm, mx_proto_id, mx_chan_id));
#else
    return (btm_sec_set_security_level (is_originator, p_name, service_id,
                                        sec_level, psm, mx_proto_id, mx_chan_id));
#endif
}