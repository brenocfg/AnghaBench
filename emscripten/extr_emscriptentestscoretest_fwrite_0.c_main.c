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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 

int main() {
  FILE *fh;

  fh = fopen("a.txt", "wb");
  if (!fh) exit(1);
  fclose(fh);

  fh = fopen("a.txt", "rb");
  if (!fh) exit(1);

  char data[] = "foobar";
  size_t written = fwrite(data, 1, sizeof(data), fh);

  printf("written=%zu\n", written);
}