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
 int /*<<< orphan*/  free (char*) ; 
 int getpart (char**,size_t*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 

int main(int argc, char **argv)
{
  char  *part;
  size_t partlen;

  if(argc< 3) {
    printf("./testpart main sub\n");
  }
  else {
    int rc = getpart(&part, &partlen, argv[1], argv[2], stdin);
    size_t i;
    if(rc)
      return rc;
    for(i = 0; i < partlen; i++)
      printf("%c", part[i]);
    free(part);
  }
  return 0;
}