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
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_append_c (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int network_mysqld_masterinfo_append_string(GString *packet, GString *s) {
	g_string_append_len(packet, S(s));
	g_string_append_c(packet, '\n');

	return 0;
}