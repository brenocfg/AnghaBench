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
struct ipsec_pcb {scalar_t__ ipsec_unit; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;

/* Variables and functions */
 struct ipsec_pcb* ifnet_softc (int /*<<< orphan*/ *) ; 

int
ipsec_interface_isvalid (ifnet_t interface)
{
    struct ipsec_pcb *pcb = NULL;
    
    if (interface == NULL)
        return 0;
    
    pcb = ifnet_softc(interface);
    
    if (pcb == NULL)
        return 0;
    
    /* When ctl disconnects, ipsec_unit is set to 0 */
    if (pcb->ipsec_unit == 0)
        return 0;
    
    return 1;
}