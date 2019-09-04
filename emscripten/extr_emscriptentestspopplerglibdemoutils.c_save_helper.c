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
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
save_helper (const gchar  *buf,
	     gsize         count,
	     gpointer      data,
	     GError      **error)
{
	gint fd = GPOINTER_TO_INT (data);

	return write (fd, buf, count) == count;
}