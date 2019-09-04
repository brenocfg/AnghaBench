#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cookie; void* rend; void* rpos; } ;
typedef  TYPE_1__ FFFILE ;

/* Variables and functions */
 char* memchr (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,size_t) ; 

__attribute__((used)) static size_t ffstring_read(FFFILE *f, unsigned char *buf, size_t len)
{
    char *src = f->cookie;
    size_t k = len+256;
    char *end = memchr(src, 0, k);

    if (end) k = end-src;
    if (k < len) len = k;
    memcpy(buf, src, len);
    f->rpos = (void *)(src+len);
    f->rend = (void *)(src+k);
    f->cookie = src+k;

    return len;
}