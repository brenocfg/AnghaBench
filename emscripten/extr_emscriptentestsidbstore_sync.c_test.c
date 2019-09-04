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
 int /*<<< orphan*/  DB ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 char* SECRET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_idb_delete (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  emscripten_idb_exists (int /*<<< orphan*/ ,char*,int*,int*) ; 
 int /*<<< orphan*/  emscripten_idb_load (int /*<<< orphan*/ ,char*,void**,int*,int*) ; 
 int /*<<< orphan*/  emscripten_idb_store (int /*<<< orphan*/ ,char*,char*,int,int*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

void test() {
  void *buffer;
  int num, error, exists;
  int sum = 0;

  printf("storing %s\n", SECRET);
  emscripten_idb_store(DB, "the_secret", SECRET, strlen(SECRET)+1, &error);
  assert(!error);
  sum++;

  printf("checking\n");
  emscripten_idb_exists(DB, "the_secret", &exists, &error);
  assert(!error);
  assert(exists);
  sum++;

  printf("loading\n");
  emscripten_idb_load(DB, "the_secret", &buffer, &num, &error);
  assert(!error);
  char *ptr = buffer;
  printf("loaded %s\n", ptr);
  assert(num == strlen(SECRET)+1);
  assert(strcmp(ptr, SECRET) == 0);
  free(buffer);
  sum++;

  printf("deleting the_secret\n");
  emscripten_idb_delete(DB, "the_secret", &error);
  assert(!error);
  sum++;

  printf("loading, should fail as we deleted\n");
  emscripten_idb_load(DB, "the_secret", &buffer, &num, &error);
  assert(error); // expected error!
  sum++;

  printf("last checking\n");
  emscripten_idb_exists(DB, "the_secret", &exists, &error);
  assert(!error);
  assert(!exists);
  sum++;

  REPORT_RESULT(sum);
}