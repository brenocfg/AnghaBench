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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 void* x (void*,int) ; 

int main(int argc, char **args)
{
    void *data;
    int len, i;

    if (argc != 3)
    {
        printf("Usage: %s <string | ip | uint32 | uint16 | uint8 | bool> <data>\n", args[0]);
        return 0;
    }

    if (strcmp(args[1], "string") == 0)
    {
        data = args[2];
        len = strlen(args[2]) + 1;
    }
    else if (strcmp(args[1], "ip") == 0)
    {
        data = calloc(1, sizeof (uint32_t));
        *((uint32_t *)data) = inet_addr(args[2]);
        len = sizeof (uint32_t);
    }
    else if (strcmp(args[1], "uint32") == 0)
    {
        data = calloc(1, sizeof (uint32_t));
        *((uint32_t *)data) = htonl((uint32_t)atoi(args[2]));
        len = sizeof (uint32_t);
    }
    else if (strcmp(args[1], "uint16") == 0)
    {
        data = calloc(1, sizeof (uint16_t));
        *((uint16_t *)data) = htons((uint16_t)atoi(args[2]));
        len = sizeof (uint16_t);
    }
    else if (strcmp(args[1], "uint8") == 0)
    {
        data = calloc(1, sizeof (uint8_t));
        *((uint8_t *)data) = atoi(args[2]);
        len = sizeof (uint8_t);
    }
    else if (strcmp(args[1], "bool") == 0)
    {
        data = calloc(1, sizeof (char));
        if (strcmp(args[2], "false") == 0)
            ((char *)data)[0] = 0;
        else if (strcmp(args[2], "true") == 0)
            ((char *)data)[0] = 1;
        else
        {
            printf("Unknown value `%s` for datatype bool!\n", args[2]);
            return -1;
        }
        len = sizeof (char);
    }
    else
    {
        printf("Unknown data type `%s`!\n", args[1]);
        return -1;
    }

    // Yes we are leaking memory, but the program is so
    // short lived that it doesn't really matter...
    printf("XOR'ing %d bytes of data...\n", len);
    data = x(data, len);
    for (i = 0; i < len; i++)
        printf("\\x%02X", ((unsigned char *)data)[i]);
    printf("\n");
}