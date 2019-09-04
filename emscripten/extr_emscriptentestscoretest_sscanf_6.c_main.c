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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char const*,char*,int*,int*,...) ; 

int main() {
  const char *date = "18.07.2013w";
  char c[10];
  memset(c, 0, 10);
  int y, m, d, i;
  i = sscanf(date, "%d.%d.%4d%c", &d, &m, &y, c);
  printf("date: %s; day %2d, month %2d, year %4d, extra: %c, %d\n", date, d, m,
         y, c[0], i);
  i = sscanf(date, "%d.%d.%3c", &d, &m, c);
  printf("date: %s; day %2d, month %2d, year %4d, extra: %s, %d\n", date, d, m,
         y, c, i);

  {
    const char *date = "18.07.2013";
    char c;
    int y, m, d, i;
    if ((i = sscanf(date, "%d.%d.%4d%c", &d, &m, &y, &c)) == 3)
    {
        printf("date: %s; day %2d, month %2d, year %4d \n", date, d, m, y);
    }
    else
    {
        printf("Error in sscanf: actually parsed %d", i);
    }
  }
}