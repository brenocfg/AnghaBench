#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* p_cmd_buf; int /*<<< orphan*/  p_user; int /*<<< orphan*/  (* p_err_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  (* p_cmd_cback ) (int /*<<< orphan*/ ,size_t,int,char*,scalar_t__) ;TYPE_1__* p_at_tbl; } ;
typedef  TYPE_2__ tBTA_AG_AT_CB ;
typedef  int UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_4__ {scalar_t__* p_cmd; int arg_type; scalar_t__ fmt; scalar_t__ max; scalar_t__ min; } ;
typedef  scalar_t__ INT16 ;

/* Variables and functions */
 int BTA_AG_AT_FREE ; 
 scalar_t__ BTA_AG_AT_INT ; 
 int BTA_AG_AT_NONE ; 
 int BTA_AG_AT_READ ; 
 int BTA_AG_AT_SET ; 
 int BTA_AG_AT_TEST ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,size_t,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,size_t,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ utl_str2int (char*) ; 
 int /*<<< orphan*/  utl_strucmp (scalar_t__*,char*) ; 

void bta_ag_process_at(tBTA_AG_AT_CB *p_cb)
{
    UINT16      idx;
    UINT8       arg_type;
    char        *p_arg;
    INT16       int_arg = 0;
    /* loop through at command table looking for match */
    for (idx = 0; p_cb->p_at_tbl[idx].p_cmd[0] != 0; idx++) {
        if (!utl_strucmp(p_cb->p_at_tbl[idx].p_cmd, p_cb->p_cmd_buf)) {
            break;
        }
    }

    /* if there is a match; verify argument type */
    if (p_cb->p_at_tbl[idx].p_cmd[0] != 0) {
        /* start of argument is p + strlen matching command */
        p_arg = p_cb->p_cmd_buf + strlen(p_cb->p_at_tbl[idx].p_cmd);
        /* if no argument */
        if (p_arg[0] == 0) {
            arg_type = BTA_AG_AT_NONE;
        }
        /* else if arg is '?' and it is last character */
        else if (p_arg[0] == '?' && p_arg[1] == 0) {
            arg_type = BTA_AG_AT_READ; /* we have a read */
        }
        /* else if arg is '=' */
        else if (p_arg[0] == '=' && p_arg[1] != 0) {
            if (p_arg[1] == '?' && p_arg[2] == 0) {
                arg_type = BTA_AG_AT_TEST; /* we have a test */
            } else {
                arg_type = BTA_AG_AT_SET; /* we have a set */
                p_arg++; /* skip past '=' */
            }
        }
        /* else it is freeform argument */
        else {
            arg_type = BTA_AG_AT_FREE;
        }
        /* if arguments match command capabilities */
        if ((arg_type & p_cb->p_at_tbl[idx].arg_type) != 0) {
            /* if it's a set integer check max, min range */
            if (arg_type == BTA_AG_AT_SET && p_cb->p_at_tbl[idx].fmt == BTA_AG_AT_INT) {
                int_arg = utl_str2int(p_arg);
                if (int_arg < (INT16) p_cb->p_at_tbl[idx].min ||
                    int_arg > (INT16) p_cb->p_at_tbl[idx].max) {
                    /* arg out of range; error */
                    (*p_cb->p_err_cback)(p_cb->p_user, FALSE, NULL);
                } else {
                    (*p_cb->p_cmd_cback)(p_cb->p_user, idx, arg_type, p_arg, int_arg);
                }
            } else {
                (*p_cb->p_cmd_cback)(p_cb->p_user, idx, arg_type, p_arg, int_arg);
            }
        } else {
            /* else error */
            (*p_cb->p_err_cback)(p_cb->p_user, FALSE, NULL);
        }
    } else {
        /* else no match call error callback */
        (*p_cb->p_err_cback)(p_cb->p_user, TRUE, p_cb->p_cmd_buf);
    }
}