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
 size_t has_E ; 
 size_t has_e ; 
 size_t has_i ; 
 size_t has_v ; 
 int /*<<< orphan*/  noextrachars (char*) ; 

__attribute__((used)) static int collectargs (char **argv, int *args) {
  int i;
  for (i = 1; argv[i] != NULL; i++) {
    if (argv[i][0] != '-')  /* not an option? */
        return i;
    switch (argv[i][1]) {  /* option */
      case '-':
        noextrachars(argv[i]);
        return (argv[i+1] != NULL ? i+1 : 0);
      case '\0':
        return i;
      case 'E':
        args[has_E] = 1;
        break;
      case 'i':
        noextrachars(argv[i]);
        args[has_i] = 1;  /* go through */
      case 'v':
        noextrachars(argv[i]);
        args[has_v] = 1;
        break;
      case 'e':
        args[has_e] = 1;  /* go through */
      case 'l':  /* both options need an argument */
        if (argv[i][2] == '\0') {  /* no concatenated argument? */
          i++;  /* try next 'argv' */
          if (argv[i] == NULL || argv[i][0] == '-')
            return -(i - 1);  /* no next argument or it is another option */
        }
        break;
      default:  /* invalid option; return its index... */
        return -i;  /* ...as a negative value */
    }
  }
  return 0;
}