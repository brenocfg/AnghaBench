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
typedef  TYPE_1__* mountlist ;
struct TYPE_3__ {char* ml_hostname; char* ml_directory; struct TYPE_3__* ml_next; } ;

/* Variables and functions */
#define  ALL 129 
#define  DIRS 128 
 scalar_t__ is_same_host (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  thisaddr ; 
 int /*<<< orphan*/  thishost ; 
 int type ; 

void
print_dump(mountlist mp)
{
  if (mp == NULL)
    return;
  if (is_same_host(mp->ml_hostname, thishost, thisaddr)) {
    switch (type) {
    case ALL:
      printf("%s:%s\n", mp->ml_hostname, mp->ml_directory);
      break;
    case DIRS:
      printf("%s\n", mp->ml_directory);
      break;
    default:
      printf("%s\n", mp->ml_hostname);
      break;
    };
  }
  if (mp->ml_next)
    print_dump(mp->ml_next);
}