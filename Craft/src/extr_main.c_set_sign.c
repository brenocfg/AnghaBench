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
 int /*<<< orphan*/  _set_sign (int,int,int,int,int,int,char const*,int) ; 
 int chunked (int) ; 
 int /*<<< orphan*/  client_sign (int,int,int,int,char const*) ; 

void set_sign(int x, int y, int z, int face, const char *text) {
    int p = chunked(x);
    int q = chunked(z);
    _set_sign(p, q, x, y, z, face, text, 1);
    client_sign(x, y, z, face, text);
}