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
struct label {int dummy; } ;

/* Variables and functions */
 int MAC_INTERNALIZE (int /*<<< orphan*/ ,struct label*,char*) ; 
 int /*<<< orphan*/  ifnet ; 

__attribute__((used)) static int
mac_ifnet_label_internalize(struct label *label, char *string)
{

	return (MAC_INTERNALIZE(ifnet, label, string));
}