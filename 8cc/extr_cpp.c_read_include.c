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
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ File ;

/* Variables and functions */
 char* dirname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  expect_newline () ; 
 char* read_cpp_header_name (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  std_include_path ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 
 scalar_t__ try_include (char*,char*,int) ; 
 char* vec_get (int /*<<< orphan*/ ,int) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_include(Token *hash, File *file, bool isimport) {
    bool std;
    char *filename = read_cpp_header_name(hash, &std);
    expect_newline();
    if (filename[0] == '/') {
        if (try_include("/", filename, isimport))
            return;
        goto err;
    }
    if (!std) {
        char *dir = file->name ? dirname(strdup(file->name)) : ".";
        if (try_include(dir, filename, isimport))
            return;
    }
    for (int i = 0; i < vec_len(std_include_path); i++)
        if (try_include(vec_get(std_include_path, i), filename, isimport))
            return;
  err:
    errort(hash, "cannot find header file: %s", filename);
}