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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t FileSize(const char* path) {
  FILE* f = fopen(path, "rb");
  int64_t retval;
  if (f == NULL) {
    return -1;
  }
  if (fseek(f, 0L, SEEK_END) != 0) {
    fclose(f);
    return -1;
  }
  retval = ftell(f);
  if (fclose(f) != 0) {
    return -1;
  }
  return retval;
}