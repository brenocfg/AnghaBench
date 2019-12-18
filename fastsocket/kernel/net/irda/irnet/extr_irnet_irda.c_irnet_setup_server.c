#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {int /*<<< orphan*/ * private; } ;
struct TYPE_8__ {int /*<<< orphan*/  ckey; int /*<<< orphan*/  stsap_sel; int /*<<< orphan*/ * file; TYPE_1__ chan; scalar_t__ ppp_open; } ;
struct TYPE_7__ {TYPE_3__ s; int /*<<< orphan*/  ias_obj; int /*<<< orphan*/  skey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  IAS_KERNEL_ATTR ; 
 int /*<<< orphan*/  IRDA_SERV_TRACE ; 
 int /*<<< orphan*/  IRNET_IAS_VALUE ; 
 int /*<<< orphan*/  IRNET_SERVICE_NAME ; 
 int /*<<< orphan*/  S_LAN ; 
 int /*<<< orphan*/  irda_irnet_create (TYPE_3__*) ; 
 int /*<<< orphan*/  irias_add_integer_attrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irias_insert_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irias_new_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_register_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_service_to_hint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_update_client (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  irnet_discovery_indication ; 
 int /*<<< orphan*/  irnet_expiry_indication ; 
 int /*<<< orphan*/  irnet_open_tsap (TYPE_3__*) ; 
 TYPE_2__ irnet_server ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline int
irnet_setup_server(void)
{
  __u16		hints;

  DENTER(IRDA_SERV_TRACE, "()\n");

  /* Initialise the regular socket part of the server */
  irda_irnet_create(&irnet_server.s);

  /* Open a local TSAP (an IrTTP instance) for the server */
  irnet_open_tsap(&irnet_server.s);

  /* PPP part setup */
  irnet_server.s.ppp_open = 0;
  irnet_server.s.chan.private = NULL;
  irnet_server.s.file = NULL;

  /* Get the hint bit corresponding to IrLAN */
  /* Note : we overload the IrLAN hint bit. As it is only a "hint", and as
   * we provide roughly the same functionality as IrLAN, this is ok.
   * In fact, the situation is similar as JetSend overloading the Obex hint
   */
  hints = irlmp_service_to_hint(S_LAN);

#ifdef ADVERTISE_HINT
  /* Register with IrLMP as a service (advertise our hint bit) */
  irnet_server.skey = irlmp_register_service(hints);
#endif /* ADVERTISE_HINT */

  /* Register with LM-IAS (so that people can connect to us) */
  irnet_server.ias_obj = irias_new_object(IRNET_SERVICE_NAME, jiffies);
  irias_add_integer_attrib(irnet_server.ias_obj, IRNET_IAS_VALUE,
			   irnet_server.s.stsap_sel, IAS_KERNEL_ATTR);
  irias_insert_object(irnet_server.ias_obj);

#ifdef DISCOVERY_EVENTS
  /* Tell IrLMP we want to be notified of newly discovered nodes */
  irlmp_update_client(irnet_server.s.ckey, hints,
		      irnet_discovery_indication, irnet_expiry_indication,
		      (void *) &irnet_server.s);
#endif

  DEXIT(IRDA_SERV_TRACE, " - self=0x%p\n", &irnet_server.s);
  return 0;
}