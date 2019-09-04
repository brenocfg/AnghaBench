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
 char* SECRET ; 
 int /*<<< orphan*/  STAGE ; 
 int /*<<< orphan*/  emscripten_idb_async_store (int /*<<< orphan*/ ,char*,char*,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int expected ; 
 int /*<<< orphan*/  ok ; 
 int /*<<< orphan*/  onerror ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  result ; 
 scalar_t__ strlen (char*) ; 

void test() {
  result = STAGE;
#if STAGE == 0
  expected = 12;
  emscripten_idb_async_store(DB, "the_secret", SECRET, strlen(SECRET)+1, (void*)expected, ok, onerror);
  printf("storing %s\n", SECRET);
#elif STAGE == 1
  expected = 31;
  emscripten_idb_async_load(DB, "the_secret", (void*)expected, onload, onerror);
#elif STAGE == 2
  expected = 44;
  emscripten_idb_async_delete(DB, "the_secret", (void*)expected, ok, onerror);
  printf("deleting the_secret\n");
#elif STAGE == 3
  expected = 55;
  emscripten_idb_async_load(DB, "the_secret", (void*)expected, onbadload, ok);
  printf("loading, should fail as we deleted\n");
#elif STAGE == 4
  expected = 66;
  emscripten_idb_async_exists(DB, "the_secret", (void*)expected, oncheck, onerror);
#elif STAGE == 5
  expected = 77;
  emscripten_idb_async_exists(DB, "the_secret", (void*)expected, onchecknope, onerror);
#else
  assert(0);
#endif
}