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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GMarkupParseContext ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_error(GMarkupParseContext *ctx, GError *error, gpointer ud)
{
    g_warning("Plist parse error: %s", error->message);
}