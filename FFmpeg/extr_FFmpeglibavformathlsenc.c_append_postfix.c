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
typedef  int /*<<< orphan*/  extension ;

/* Variables and functions */
 char* POSTFIX_PATTERN ; 
 int /*<<< orphan*/  av_strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int append_postfix(char *name, int name_buf_len, int i)
{
    char *p;
    char extension[10] = {'\0'};

    p = strrchr(name, '.');
    if (p) {
        av_strlcpy(extension, p, sizeof(extension));
        *p = '\0';
    }

    snprintf(name + strlen(name), name_buf_len - strlen(name), POSTFIX_PATTERN, i);

    if (strlen(extension))
        av_strlcat(name, extension, name_buf_len);

    return 0;
}