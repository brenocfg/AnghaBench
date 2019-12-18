#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s_addr; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  in6p_faddr; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  in6p_laddr; int /*<<< orphan*/  inp_lport; TYPE_6__ inp_faddr; TYPE_3__ inp_laddr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_4__ ia46_addr4; } ;
struct TYPE_16__ {int /*<<< orphan*/  addr6; TYPE_5__ addr46; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {TYPE_1__ ia46_addr4; } ;
struct TYPE_15__ {int /*<<< orphan*/  addr6; TYPE_2__ addr46; } ;
struct cfil_hash_entry {int /*<<< orphan*/  cfentry_family; TYPE_8__ cfentry_faddr; int /*<<< orphan*/  cfentry_fport; TYPE_7__ cfentry_laddr; int /*<<< orphan*/  cfentry_lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int FALSE ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int TRUE ; 

__attribute__((used)) static bool
fill_cfil_hash_entry_from_inp(struct cfil_hash_entry *entry, bool isLocal, struct inpcb *inp)
{
    if (entry == NULL || inp == NULL) {
        return FALSE;
    }
    
    if (inp->inp_vflag & INP_IPV4) {
        if (isLocal == TRUE) {
            entry->cfentry_lport = inp->inp_lport;
            entry->cfentry_laddr.addr46.ia46_addr4.s_addr = inp->inp_laddr.s_addr;
        } else {
            entry->cfentry_fport = inp->inp_fport;
            entry->cfentry_faddr.addr46.ia46_addr4.s_addr = inp->inp_faddr.s_addr;
        }
        entry->cfentry_family = AF_INET;
        return TRUE;
    } else if (inp->inp_vflag & INP_IPV6) {
        if (isLocal == TRUE) {
            entry->cfentry_lport = inp->inp_lport;
            entry->cfentry_laddr.addr6 = inp->in6p_laddr;
        } else {
            entry->cfentry_fport = inp->inp_fport;
            entry->cfentry_faddr.addr6 = inp->in6p_faddr;
        }
        entry->cfentry_family = AF_INET6;
        return TRUE;
    }
    return FALSE;
}