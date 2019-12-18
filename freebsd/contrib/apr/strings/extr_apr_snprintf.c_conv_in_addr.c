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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 char* conv_10 (unsigned int,int /*<<< orphan*/ ,int*,char*,int*) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *conv_in_addr(struct in_addr *ia, char *buf_end, apr_size_t *len)
{
    unsigned addr = ntohl(ia->s_addr);
    char *p = buf_end;
    int is_negative;
    apr_size_t sub_len;

    p = conv_10((addr & 0x000000FF)      , TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0x0000FF00) >>  8, TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0x00FF0000) >> 16, TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0xFF000000) >> 24, TRUE, &is_negative, p, &sub_len);

    *len = buf_end - p;
    return (p);
}