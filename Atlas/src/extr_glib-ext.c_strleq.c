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
typedef  scalar_t__ gsize ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int gboolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 

gboolean strleq(const gchar *a, gsize a_len, const gchar *b, gsize b_len) {
	if (a_len != b_len) return FALSE;
	return (0 == memcmp(a, b, a_len));
}