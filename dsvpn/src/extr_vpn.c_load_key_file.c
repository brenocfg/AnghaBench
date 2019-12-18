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
struct TYPE_3__ {int /*<<< orphan*/  uc_kx_st; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int safe_read (int,unsigned char*,int,int) ; 
 int /*<<< orphan*/  uc_memzero (unsigned char*,int) ; 
 int /*<<< orphan*/  uc_state_init (int /*<<< orphan*/ ,unsigned char*,unsigned char const*) ; 

__attribute__((used)) static int load_key_file(Context *context, const char *file)
{
    unsigned char key[32];
    int           fd;

    if ((fd = open(file, O_RDONLY)) == -1) {
        return -1;
    }
    if (safe_read(fd, key, sizeof key, -1) != sizeof key) {
        (void) close(fd);
        return -1;
    }
    uc_state_init(context->uc_kx_st, key, (const unsigned char *) "VPN Key Exchange");
    uc_memzero(key, sizeof key);

    return close(fd);
}