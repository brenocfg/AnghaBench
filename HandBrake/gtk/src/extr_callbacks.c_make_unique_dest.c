#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_7__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append_printf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_printf (TYPE_1__*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static void
make_unique_dest(const gchar *dest_dir, GString *str, const gchar * extension)
{
    GString * uniq = g_string_new(str->str);
    int       copy = 0;

    g_string_printf(uniq, "%s/%s.%s", dest_dir, str->str, extension);
    while (g_file_test(uniq->str, G_FILE_TEST_EXISTS))
    {
        g_string_printf(uniq, "%s/%s (%d).%s", dest_dir, str->str, ++copy, extension);
    }
    if (copy)
    {
        g_string_append_printf(str, " (%d)", copy);
    }
    g_string_free(uniq, TRUE);
}