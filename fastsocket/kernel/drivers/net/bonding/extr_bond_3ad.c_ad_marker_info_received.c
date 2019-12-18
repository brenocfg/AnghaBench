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
struct port {int /*<<< orphan*/  actor_port_number; } ;
struct bond_marker {int /*<<< orphan*/  tlv_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_MARKER_RESPONSE_SUBTYPE ; 
 scalar_t__ ad_marker_send (struct port*,struct bond_marker*) ; 
 int /*<<< orphan*/  memcpy (struct bond_marker*,struct bond_marker*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_marker_info_received(struct bond_marker *marker_info,
	struct port *port)
{
	struct bond_marker marker;

	// copy the received marker data to the response marker
	//marker = *marker_info;
	memcpy(&marker, marker_info, sizeof(struct bond_marker));
	// change the marker subtype to marker response
	marker.tlv_type=AD_MARKER_RESPONSE_SUBTYPE;
	// send the marker response

	if (ad_marker_send(port, &marker) >= 0) {
		pr_debug("Sent Marker Response on port %d\n", port->actor_port_number);
	}
}