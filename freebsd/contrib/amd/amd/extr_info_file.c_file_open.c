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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static FILE *
file_open(char *map, time_t *tp)
{
  FILE *mapf = fopen(map, "r");

  if (mapf && tp) {
    struct stat stb;
    if (fstat(fileno(mapf), &stb) < 0)
      *tp = clocktime(NULL);
    else
      *tp = stb.st_mtime;
  }
  return mapf;
}