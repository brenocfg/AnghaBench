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
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

int matchPrompt(char *bufStr)
{
    int i = 0, q = 0;
    char *prompts = ":>%$#";
    
    char *tmpStr = malloc(strlen(bufStr) + 1);
    memset(tmpStr, 0, strlen(bufStr) + 1);
    
    // ayy lmao copy pasta for removing ansi shit
    char in_escape = 0;
    for (i = 0; i < strlen(bufStr); i++)
    {
        if (bufStr[i] == '\x1B')
        {
            if (in_escape == 0) 
                in_escape = 1;
        } else if ((in_escape == 1) && (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", bufStr[i]) != NULL))
        {
            in_escape = 0;
        } else if (in_escape == 0) 
        {
            strncat(tmpStr, &(bufStr[i]), 1);
        }
    }
    
    int bufLen = strlen(tmpStr);
    for(i = 0; i < strlen(prompts); i++)
    {
        while(bufLen > q && (*(tmpStr + bufLen - q) == 0x00 || *(tmpStr + bufLen - q) == ' ' || *(tmpStr + bufLen - q) == '\r' || *(tmpStr + bufLen - q) == '\n')) q++;
        
        if(*(tmpStr + bufLen - q) == prompts[i])
        {
            free(tmpStr);
            return 1;
        }           
    }
    
    free(tmpStr);
    return 0;
}