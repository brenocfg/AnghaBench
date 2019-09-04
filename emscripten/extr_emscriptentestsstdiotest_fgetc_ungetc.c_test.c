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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int feof (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int ungetc (char,int /*<<< orphan*/ *) ; 

void test() {
  FILE *file;
  int err;
  char buffer[256];

  file = fopen("/tmp/file.txt", "r");
  assert(file);

  // pushing EOF always returns EOF
  rewind(file);
  err = ungetc(EOF, file);
  assert(err == EOF);

  // ungetc should return itself
  err = ungetc('a', file);
  assert(err == (int)'a');

  // fgetc should get it (note that we cannot push more than 1, as there is no portability guarantee for that)
  err = fgetc(file);
  assert(err == (int)'a');

  // fread should get it first
  ungetc('b', file);
  int r = fread(buffer, sizeof(char), sizeof(buffer), file);
  assert(r == 3);
  buffer[3] = 0;
  assert(!strcmp(buffer, "bcd"));

  // rewind and fseek should reset anything that's been
  // pushed to the stream
  ungetc('a', file);
  rewind(file);
  err = fgetc(file);
  assert(err == (int)'c');
  ungetc('a', file);
  fseek(file, 0, SEEK_SET);
  err = fgetc(file);
  assert(err == (int)'c');

  // fgetc, when nothing is left, should return EOF
  fseek(file, 0, SEEK_END);
  err = fgetc(file);
  assert(err == EOF);
  err = feof(file);
  assert(err);

  // ungetc should reset the EOF indicator
  ungetc('e', file);
  err = feof(file);
  // XXX musl fails here. it does not allow ungetc on a stream in EOF mode, which has been confirmed as a bug upstream

  fclose(file);

  puts("success");
}