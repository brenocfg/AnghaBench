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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_EXECUTABLE ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_SYMLINK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * g_build_filename (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_read_name (int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_pattern_match_simple (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guess_arch_of_file (int /*<<< orphan*/ *,int*) ; 

void find_arch(const gchar *real_path, const gchar *pattern, bool* archs) {
    GDir *dir;
    gchar *full_name;
    dir = g_dir_open(real_path, 0, NULL);
    if (dir != NULL) {
        const gchar *entry;
        while ((entry = g_dir_read_name(dir)) != NULL) {
            full_name = g_build_filename(real_path, entry, NULL);
            if (g_file_test(full_name, G_FILE_TEST_IS_SYMLINK)) {
            } else if (g_file_test(full_name, G_FILE_TEST_IS_DIR)) {
                find_arch(full_name, pattern, archs);
            } else if (g_file_test(full_name, G_FILE_TEST_IS_EXECUTABLE) || g_pattern_match_simple(pattern, entry) ) {
                guess_arch_of_file(full_name, archs);
            }
        }
        g_dir_close(dir);
    }
    else {
        g_warning("%s: %s", real_path, g_strerror(errno));
    }
}