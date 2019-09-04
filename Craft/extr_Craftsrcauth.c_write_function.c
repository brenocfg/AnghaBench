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
 scalar_t__ MAX_RESPONSE_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,scalar_t__) ; 

size_t write_function(char *data, size_t size, size_t count, void *arg) {
    size_t length = size * count;
    char *dst = (char *)arg;
    char *src = malloc(length + 1);
    memcpy(src, data, length);
    src[length] = '\0';
    strncat(dst, src, MAX_RESPONSE_LENGTH - strlen(dst) - 1);
    free(src);
    return length;
}