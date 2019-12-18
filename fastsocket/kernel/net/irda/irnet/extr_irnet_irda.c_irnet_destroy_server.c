#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s; scalar_t__ ias_obj; int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IRDA_SERV_TRACE ; 
 int /*<<< orphan*/  irda_irnet_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irias_delete_object (scalar_t__) ; 
 int /*<<< orphan*/  irlmp_unregister_service (int /*<<< orphan*/ ) ; 
 TYPE_1__ irnet_server ; 

__attribute__((used)) static inline void
irnet_destroy_server(void)
{
  DENTER(IRDA_SERV_TRACE, "()\n");

#ifdef ADVERTISE_HINT
  /* Unregister with IrLMP */
  irlmp_unregister_service(irnet_server.skey);
#endif /* ADVERTISE_HINT */

  /* Unregister with LM-IAS */
  if(irnet_server.ias_obj)
    irias_delete_object(irnet_server.ias_obj);

  /* Cleanup the socket part */
  irda_irnet_destroy(&irnet_server.s);

  DEXIT(IRDA_SERV_TRACE, "\n");
  return;
}