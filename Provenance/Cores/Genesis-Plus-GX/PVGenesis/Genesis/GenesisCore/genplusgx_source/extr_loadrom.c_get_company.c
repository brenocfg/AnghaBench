#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ company; int /*<<< orphan*/  companyid; } ;
struct TYPE_3__ {char* copyright; } ;

/* Variables and functions */
 int MAXCOMPANY ; 
 TYPE_2__* companyinfo ; 
 TYPE_1__ rominfo ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strstr (char*,char*) ; 

char *get_company(void)
{
  char *s;
  int i;
  char company[10];

  for (i = 3; i < 8; i++) 
  {
    company[i - 3] = rominfo.copyright[i];
  }
  company[5] = 0;

  /** OK, first look for a hyphen
   *  Capcom use T-12 for example
   */
  s = strstr (company, "-");
  if (s != NULL)
  {
    s++;
    strcpy (company, s);
  }

  /** Strip any trailing spaces **/
  for (i = strlen (company) - 1; i >= 0; i--)
    if (company[i] == 32)
      company[i] = 0;

  if (strlen (company) == 0)
    return (char *)companyinfo[MAXCOMPANY - 1].company;

  for (i = 0; i < MAXCOMPANY - 1; i++)
  {
    if (!(strncmp (company, companyinfo[i].companyid, strlen (company))))
      return (char *)companyinfo[i].company;
  }

  return (char *)companyinfo[MAXCOMPANY - 1].company;
}