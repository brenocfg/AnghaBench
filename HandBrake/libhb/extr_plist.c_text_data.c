#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_2__ {char* value; } ;
typedef  TYPE_1__ parse_data_t ;

/* Variables and functions */
 char* realloc (char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
text_data(
    void *ud,
    const xmlChar *xtext,
    int len)
{
    char *text = (char*)xtext;
    parse_data_t *pd = (parse_data_t*)ud;

    int pos = 0;
    if (pd->value != NULL)
    {
        pos = strlen(pd->value);
    }
    char *tmp = realloc(pd->value, pos + len + 1);
    if (tmp == NULL)
        return;
    pd->value = tmp;
    strncpy(pd->value + pos, text, len);
    pd->value[pos + len] = 0;
}