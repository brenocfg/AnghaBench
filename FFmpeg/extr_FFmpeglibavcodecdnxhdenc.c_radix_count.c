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
typedef  int /*<<< orphan*/  buckets ;
struct TYPE_3__ {int value; } ;
typedef  TYPE_1__ RCCMPEntry ;

/* Variables and functions */
 int BUCKET_BITS ; 
 int NBUCKETS ; 
 int RADIX_PASSES ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 size_t get_bucket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void radix_count(const RCCMPEntry *data, int size,
                        int buckets[RADIX_PASSES][NBUCKETS])
{
    int i, j;
    memset(buckets, 0, sizeof(buckets[0][0]) * RADIX_PASSES * NBUCKETS);
    for (i = 0; i < size; i++) {
        int v = data[i].value;
        for (j = 0; j < RADIX_PASSES; j++) {
            buckets[j][get_bucket(v, 0)]++;
            v >>= BUCKET_BITS;
        }
        av_assert1(!v);
    }
    for (j = 0; j < RADIX_PASSES; j++) {
        int offset = size;
        for (i = NBUCKETS - 1; i >= 0; i--)
            buckets[j][i] = offset -= buckets[j][i];
        av_assert1(!buckets[j][0]);
    }
}