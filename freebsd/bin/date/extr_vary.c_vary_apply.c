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
struct vary {char* arg; struct vary* next; } ;
struct tm {int tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjday (struct tm*,char,int,int) ; 
 int /*<<< orphan*/  adjhour (struct tm*,char,int,int) ; 
 int /*<<< orphan*/  adjmin (struct tm*,char,int,int) ; 
 int /*<<< orphan*/  adjmon (struct tm*,char,int,int,int) ; 
 int /*<<< orphan*/  adjsec (struct tm*,char,int,int) ; 
 int /*<<< orphan*/  adjwday (struct tm*,char,int,int,int) ; 
 int /*<<< orphan*/  adjyear (struct tm*,char,int,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  digits ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,int /*<<< orphan*/ ) ; 
 int trans (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trans_mon ; 
 int /*<<< orphan*/  trans_wday ; 

const struct vary *
vary_apply(const struct vary *v, struct tm *t)
{
  char type;
  char which;
  char *arg;
  size_t len;
  int val;

  for (; v; v = v->next) {
    type = *v->arg;
    arg = v->arg;
    if (type == '+' || type == '-')
      arg++;
    else
      type = '\0';
    len = strlen(arg);
    if (len < 2)
      return v;

    if (type == '\0')
      t->tm_isdst = -1;

    if (strspn(arg, digits) != len-1) {
      val = trans(trans_wday, arg);
      if (val != -1) {
          if (!adjwday(t, type, val, 1, 1))
            return v;
      } else {
        val = trans(trans_mon, arg);
        if (val != -1) {
          if (!adjmon(t, type, val, 1, 1))
            return v;
        } else
          return v;
      }
    } else {
      val = atoi(arg);
      which = arg[len-1];
      
      switch (which) {
        case 'S':
          if (!adjsec(t, type, val, 1))
            return v;
          break;
        case 'M':
          if (!adjmin(t, type, val, 1))
            return v;
          break;
        case 'H':
          if (!adjhour(t, type, val, 1))
            return v;
          break;
        case 'd':
          t->tm_isdst = -1;
          if (!adjday(t, type, val, 1))
            return v;
          break;
        case 'w':
          t->tm_isdst = -1;
          if (!adjwday(t, type, val, 0, 1))
            return v;
          break;
        case 'm':
          t->tm_isdst = -1;
          if (!adjmon(t, type, val, 0, 1))
            return v;
          break;
        case 'y':
          t->tm_isdst = -1;
          if (!adjyear(t, type, val, 1))
            return v;
          break;
        default:
          return v;
      }
    }
  }
  return 0;
}