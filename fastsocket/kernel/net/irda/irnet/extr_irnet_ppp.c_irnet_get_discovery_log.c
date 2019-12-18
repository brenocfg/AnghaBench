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
struct TYPE_3__ {int disco_number; int /*<<< orphan*/ * discoveries; } ;
typedef  TYPE_1__ irnet_socket ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_INFO ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DISCOVERY_DEFAULT_SLOTS ; 
 int /*<<< orphan*/  S_LAN ; 
 int /*<<< orphan*/ * irlmp_get_discoveries (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_service_to_hint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
irnet_get_discovery_log(irnet_socket *	ap)
{
  __u16		mask = irlmp_service_to_hint(S_LAN);

  /* Ask IrLMP for the current discovery log */
  ap->discoveries = irlmp_get_discoveries(&ap->disco_number, mask,
					  DISCOVERY_DEFAULT_SLOTS);

  /* Check if the we got some results */
  if(ap->discoveries == NULL)
    ap->disco_number = -1;

  DEBUG(CTRL_INFO, "Got the log (0x%p), size is %d\n",
	ap->discoveries, ap->disco_number);
}