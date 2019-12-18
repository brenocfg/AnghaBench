#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct pcmcia_socket {int state; TYPE_1__* ops; } ;
struct pcmcia_device {TYPE_3__* function_config; } ;
struct TYPE_6__ {scalar_t__ CardState; scalar_t__ SocketState; } ;
typedef  TYPE_2__ cs_status_t ;
struct TYPE_7__ {int state; int IntType; int CardValues; int ConfigBase; } ;
typedef  TYPE_3__ config_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_status ) (struct pcmcia_socket*,int*) ;} ;

/* Variables and functions */
 int CISREG_ESR ; 
 int CISREG_PRR ; 
 int CONFIG_LOCKED ; 
 scalar_t__ CS_EVENT_3VCARD ; 
 scalar_t__ CS_EVENT_BATTERY_DEAD ; 
 scalar_t__ CS_EVENT_BATTERY_LOW ; 
 scalar_t__ CS_EVENT_CARD_DETECT ; 
 scalar_t__ CS_EVENT_CB_DETECT ; 
 scalar_t__ CS_EVENT_PM_SUSPEND ; 
 scalar_t__ CS_EVENT_READY_CHANGE ; 
 scalar_t__ CS_EVENT_REQUEST_ATTENTION ; 
 scalar_t__ CS_EVENT_WRITE_PROTECT ; 
 scalar_t__ CS_EVENT_XVCARD ; 
 int ENODEV ; 
 int ESR_REQ_ATTN ; 
 int INT_MEMORY_AND_IO ; 
 int INT_ZOOMED_VIDEO ; 
 int PRESENT_EXT_STATUS ; 
 int PRESENT_PIN_REPLACE ; 
 int PRR_BVD1_STATUS ; 
 int PRR_BVD2_STATUS ; 
 int PRR_READY_STATUS ; 
 int PRR_WP_STATUS ; 
 int SOCKET_PRESENT ; 
 int SOCKET_SUSPEND ; 
 int SS_3VCARD ; 
 int SS_BATDEAD ; 
 int SS_BATWARN ; 
 int SS_CARDBUS ; 
 int SS_DETECT ; 
 int SS_READY ; 
 int SS_WRPROT ; 
 int SS_XVCARD ; 
 int /*<<< orphan*/  pcmcia_read_cis_mem (struct pcmcia_socket*,int,int,int,int*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,int*) ; 

__attribute__((used)) static int pccard_get_status(struct pcmcia_socket *s,
			     struct pcmcia_device *p_dev,
			     cs_status_t *status)
{
	config_t *c;
	int val;

	s->ops->get_status(s, &val);
	status->CardState = status->SocketState = 0;
	status->CardState |= (val & SS_DETECT) ? CS_EVENT_CARD_DETECT : 0;
	status->CardState |= (val & SS_CARDBUS) ? CS_EVENT_CB_DETECT : 0;
	status->CardState |= (val & SS_3VCARD) ? CS_EVENT_3VCARD : 0;
	status->CardState |= (val & SS_XVCARD) ? CS_EVENT_XVCARD : 0;
	if (s->state & SOCKET_SUSPEND)
		status->CardState |= CS_EVENT_PM_SUSPEND;
	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;

	c = (p_dev) ? p_dev->function_config : NULL;

	if ((c != NULL) && (c->state & CONFIG_LOCKED) &&
	    (c->IntType & (INT_MEMORY_AND_IO | INT_ZOOMED_VIDEO))) {
		u_char reg;
		if (c->CardValues & PRESENT_PIN_REPLACE) {
			pcmcia_read_cis_mem(s, 1, (c->ConfigBase+CISREG_PRR)>>1, 1, &reg);
			status->CardState |=
				(reg & PRR_WP_STATUS) ? CS_EVENT_WRITE_PROTECT : 0;
			status->CardState |=
				(reg & PRR_READY_STATUS) ? CS_EVENT_READY_CHANGE : 0;
			status->CardState |=
				(reg & PRR_BVD2_STATUS) ? CS_EVENT_BATTERY_LOW : 0;
			status->CardState |=
				(reg & PRR_BVD1_STATUS) ? CS_EVENT_BATTERY_DEAD : 0;
		} else {
			/* No PRR?  Then assume we're always ready */
			status->CardState |= CS_EVENT_READY_CHANGE;
		}
		if (c->CardValues & PRESENT_EXT_STATUS) {
			pcmcia_read_cis_mem(s, 1, (c->ConfigBase+CISREG_ESR)>>1, 1, &reg);
			status->CardState |=
				(reg & ESR_REQ_ATTN) ? CS_EVENT_REQUEST_ATTENTION : 0;
		}
		return 0;
	}
	status->CardState |=
		(val & SS_WRPROT) ? CS_EVENT_WRITE_PROTECT : 0;
	status->CardState |=
		(val & SS_BATDEAD) ? CS_EVENT_BATTERY_DEAD : 0;
	status->CardState |=
		(val & SS_BATWARN) ? CS_EVENT_BATTERY_LOW : 0;
	status->CardState |=
		(val & SS_READY) ? CS_EVENT_READY_CHANGE : 0;
	return 0;
}