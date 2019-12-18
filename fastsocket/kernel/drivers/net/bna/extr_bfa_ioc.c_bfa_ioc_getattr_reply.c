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
struct bfi_ioc_attr {int /*<<< orphan*/  maxfrsize; void* card_type; void* adapter_prop; } ;
struct bfa_ioc {struct bfi_ioc_attr* attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_E_FWRSP_GETATTR ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_ioc*,int /*<<< orphan*/ ) ; 
 void* ntohl (void*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_getattr_reply(struct bfa_ioc *ioc)
{
	struct bfi_ioc_attr *attr = ioc->attr;

	attr->adapter_prop  = ntohl(attr->adapter_prop);
	attr->card_type     = ntohl(attr->card_type);
	attr->maxfrsize	    = ntohs(attr->maxfrsize);

	bfa_fsm_send_event(ioc, IOC_E_FWRSP_GETATTR);
}