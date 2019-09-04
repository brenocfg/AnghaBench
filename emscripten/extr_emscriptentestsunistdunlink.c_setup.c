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

/* Variables and functions */
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  create_file (char*,char*,int) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 

void setup() {
  mkdir("working", 0777);
#ifdef __EMSCRIPTEN__

#ifdef __EMSCRIPTEN_ASMFS__
  mkdir("working", 0777);
#else
  EM_ASM(
#if NODEFS
    FS.mount(NODEFS, { root: '.' }, 'working');
#endif
  );
#endif
#endif
  chdir("working");
  create_file("file", "test", 0777);
  create_file("file1", "test", 0777);
#ifndef NO_SYMLINK
  symlink("file1", "file1-link");
#endif
  mkdir("dir-empty", 0777);
#ifndef NO_SYMLINK
  symlink("dir-empty", "dir-empty-link");
#endif
  mkdir("dir-readonly", 0777);
  create_file("dir-readonly/anotherfile", "test", 0777);
  mkdir("dir-readonly/anotherdir", 0777);
  chmod("dir-readonly", 0555);
  mkdir("dir-full", 0777);
  create_file("dir-full/anotherfile", "test", 0777);
}