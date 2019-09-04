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
 int /*<<< orphan*/  emscripten_idb_free_blob (int) ; 
 int /*<<< orphan*/  emscripten_idb_load (int /*<<< orphan*/ ,char*,void**,int*,int*) ; 
 int /*<<< orphan*/  emscripten_idb_load_blob (int /*<<< orphan*/ ,char*,int*,int*) ; 
 int /*<<< orphan*/  emscripten_idb_read_from_blob (int,int /*<<< orphan*/ ,int const,void*) ; 
 int /*<<< orphan*/  emscripten_idb_store (int /*<<< orphan*/ ,char*,char*,int,int*) ; 
 int /*<<< orphan*/  emscripten_idb_store_blob (int /*<<< orphan*/ ,char*,void*,int const,int*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int const) ; 
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

  // worker-specific code

  printf("save blobs\n");
  const int CHUNK = /*50*/1*1024*1024;
  buffer = malloc(CHUNK);
  char *cbuffer = (char*)buffer;
  cbuffer[0] = 1;
  emscripten_idb_store_blob(DB, "chunk1", buffer, CHUNK, &error);
  cbuffer[0] = 2;
  emscripten_idb_store_blob(DB, "chunk2", buffer, CHUNK, &error);
  assert(!error);
  printf("blobs stored\n");
  cbuffer[0] = 0;
  int blob1, blob2;
  printf("load first\n");
  emscripten_idb_load_blob(DB, "chunk1", &blob1, &error);
  printf("loaded first as %d\n", blob1);
  assert(!error);
  printf("load second\n");
  emscripten_idb_load_blob(DB, "chunk2", &blob2, &error);
  printf("loaded second as %d\n", blob2);
  assert(!error);
  printf("blobs loaded\n");
  emscripten_idb_read_from_blob(blob1, 0, CHUNK, buffer);
  printf("read %d\n", cbuffer[0]);
  assert(cbuffer[0] == 1);
  printf("moving on\n");
  emscripten_idb_read_from_blob(blob2, 0, CHUNK, buffer);
  printf("read %d\n", cbuffer[0]);
  assert(cbuffer[0] == 2);
  //EM_ASM({ alert('freeze') });
  printf("freeing blobs\n");
  emscripten_idb_free_blob(blob1);
  emscripten_idb_free_blob(blob2);

  // finish up

  REPORT_RESULT(sum);
}