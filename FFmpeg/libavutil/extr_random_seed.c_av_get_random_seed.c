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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BCRYPT_ALG_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  BCRYPT_RNG_ALGORITHM ; 
 scalar_t__ BCRYPT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCryptCloseAlgorithmProvider (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCryptGenRandom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCryptOpenAlgorithmProvider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_PRIMITIVE_PROVIDER ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  get_generic_seed () ; 
 int read_random (int /*<<< orphan*/ *,char*) ; 

uint32_t av_get_random_seed(void)
{
    uint32_t seed;

#if HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    if (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (UCHAR*)&seed, sizeof(seed), 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        if (BCRYPT_SUCCESS(ret))
            return seed;
    }
#endif

#if HAVE_ARC4RANDOM
    return arc4random();
#endif

    if (read_random(&seed, "/dev/urandom") == sizeof(seed))
        return seed;
    if (read_random(&seed, "/dev/random")  == sizeof(seed))
        return seed;
    return get_generic_seed();
}