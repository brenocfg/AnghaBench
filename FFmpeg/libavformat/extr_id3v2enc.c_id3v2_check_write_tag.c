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
typedef  scalar_t__ uint32_t ;
typedef  enum ID3v2Encoding { ____Placeholder_ID3v2Encoding } ID3v2Encoding ;
struct TYPE_3__ {char* key; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  ID3v2EncContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVDictionaryEntry ;

/* Variables and functions */
 scalar_t__ AV_RB32 (char const*) ; 
 int id3v2_put_ttag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int id3v2_check_write_tag(ID3v2EncContext *id3, AVIOContext *pb, AVDictionaryEntry *t,
                                 const char table[][4], enum ID3v2Encoding enc)
{
    uint32_t tag;
    int i;

    if (t->key[0] != 'T' || strlen(t->key) != 4)
        return -1;
    tag = AV_RB32(t->key);
    for (i = 0; *table[i]; i++)
        if (tag == AV_RB32(table[i]))
            return id3v2_put_ttag(id3, pb, t->value, NULL, tag, enc);
    return -1;
}