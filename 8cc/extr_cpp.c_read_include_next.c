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
typedef  int /*<<< orphan*/  Token ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ File ;

/* Variables and functions */
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  expect_newline () ; 
 int /*<<< orphan*/  format (char*,char*,char*) ; 
 char* fullpath (int /*<<< orphan*/ ) ; 
 char* read_cpp_header_name (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  std_include_path ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ try_include (char*,char*,int) ; 
 char* vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_include_next(Token *hash, File *file) {
    // [GNU] #include_next is a directive to include the "next" file
    // from the search path. This feature is used to override a
    // header file without getting into infinite inclusion loop.
    // This directive doesn't distinguish <> and "".
    bool std;
    char *filename = read_cpp_header_name(hash, &std);
    expect_newline();
    if (filename[0] == '/') {
        if (try_include("/", filename, false))
            return;
        goto err;
    }
    char *cur = fullpath(file->name);
    int i = 0;
    for (; i < vec_len(std_include_path); i++) {
        char *dir = vec_get(std_include_path, i);
        if (!strcmp(cur, fullpath(format("%s/%s", dir, filename))))
            break;
    }
    for (i++; i < vec_len(std_include_path); i++)
        if (try_include(vec_get(std_include_path, i), filename, false))
            return;
  err:
    errort(hash, "cannot find header file: %s", filename);
}