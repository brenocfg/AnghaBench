#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_2__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  transactionNumber; int /*<<< orphan*/  initiatorNodeIdentifier; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ DistributedTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  hash_any (unsigned char*,int) ; 
 int /*<<< orphan*/  hash_combine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_uint32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
DistributedTransactionIdHash(const void *key, Size keysize)
{
	DistributedTransactionId *entry = (DistributedTransactionId *) key;
	uint32 hash = 0;

	hash = hash_uint32(entry->initiatorNodeIdentifier);
	hash = hash_combine(hash, hash_any((unsigned char *) &entry->transactionNumber,
									   sizeof(int64)));
	hash = hash_combine(hash, hash_any((unsigned char *) &entry->timestamp,
									   sizeof(TimestampTz)));

	return hash;
}