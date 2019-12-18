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
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_mpi_write_string (int /*<<< orphan*/  const*,int,char*,int,size_t*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

void mbedtls_mpi_printf(const char *name, const mbedtls_mpi *X)
{
    static char buf[1024];
    size_t n;
    memset(buf, 0, sizeof(buf));
    mbedtls_mpi_write_string(X, 16, buf, sizeof(buf)-1, &n);
    if(n) {
        printf("%s = 0x%s\n", name, buf);
    } else {
        printf("%s = TOOLONG\n", name);
    }
}