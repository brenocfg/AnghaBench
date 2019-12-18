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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int put_address(char *st, u_char *p, int len)
{ u_char retval = 0;
  u_char adr_typ = 0; /* network standard */

  if (len < 2) return(retval);
  if (*p == 0xA1)
   { retval = *(++p) + 2; /* total length */
     if (retval > len) return(0); /* too short */
     len = retval - 2; /* remaining length */
     if (len < 3) return(0);
     if ((*(++p) != 0x0A) || (*(++p) != 1)) return(0);
     adr_typ = *(++p);
     len -= 3;
     p++;
     if (len < 2) return(0);
     if (*p++ != 0x12) return(0);
     if (*p > len) return(0); /* check number length */
     len = *p++;
   }   
  else
   if (*p == 0x80)
    { retval = *(++p) + 2; /* total length */
      if (retval > len) return(0);
      len = retval - 2;
      p++;
    }
   else  
    return(0); /* invalid address information */

  sprintf(st,"%d ",adr_typ);
  st += strlen(st);
  if (!len) 
    *st++ = '-';
  else
   while (len--)
     *st++ = *p++;
  *st = '\0';
  return(retval);
}