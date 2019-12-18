#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ num_transforms; } ;
struct TYPE_4__ {int /*<<< orphan*/  cutoffTransforms; int /*<<< orphan*/  cutoffTransformsCount; int /*<<< orphan*/  dict_words; int /*<<< orphan*/  buckets; int /*<<< orphan*/  hash_table_lengths; int /*<<< orphan*/  hash_table_words; scalar_t__ num_transforms; int /*<<< orphan*/  words; } ;
typedef  TYPE_1__ BrotliEncoderDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliGetDictionary () ; 
 TYPE_3__* BrotliGetTransforms () ; 
 int /*<<< orphan*/  kCutoffTransforms ; 
 int /*<<< orphan*/  kCutoffTransformsCount ; 
 int /*<<< orphan*/  kStaticDictionaryBuckets ; 
 int /*<<< orphan*/  kStaticDictionaryHashLengths ; 
 int /*<<< orphan*/  kStaticDictionaryHashWords ; 
 int /*<<< orphan*/  kStaticDictionaryWords ; 

void BrotliInitEncoderDictionary(BrotliEncoderDictionary* dict) {
  dict->words = BrotliGetDictionary();
  dict->num_transforms = (uint32_t)BrotliGetTransforms()->num_transforms;

  dict->hash_table_words = kStaticDictionaryHashWords;
  dict->hash_table_lengths = kStaticDictionaryHashLengths;
  dict->buckets = kStaticDictionaryBuckets;
  dict->dict_words = kStaticDictionaryWords;

  dict->cutoffTransformsCount = kCutoffTransformsCount;
  dict->cutoffTransforms = kCutoffTransforms;
}