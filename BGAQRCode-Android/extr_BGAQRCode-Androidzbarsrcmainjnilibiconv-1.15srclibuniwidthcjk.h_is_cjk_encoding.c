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
 scalar_t__ STREQ_OPT (char const*,char*,char,char,char,char,char,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_cjk_encoding (const char *encoding)
{
  if (0
      /* Legacy Japanese encodings */
      || STREQ_OPT (encoding, "EUC-JP", 'E', 'U', 'C', '-', 'J', 'P', 0, 0, 0)
      /* Legacy Chinese encodings */
      || STREQ_OPT (encoding, "GB2312", 'G', 'B', '2', '3', '1', '2', 0, 0, 0)
      || STREQ_OPT (encoding, "GBK", 'G', 'B', 'K', 0, 0, 0, 0, 0, 0)
      || STREQ_OPT (encoding, "EUC-TW", 'E', 'U', 'C', '-', 'T', 'W', 0, 0, 0)
      || STREQ_OPT (encoding, "BIG5", 'B', 'I', 'G', '5', 0, 0, 0, 0, 0)
      /* Legacy Korean encodings */
      || STREQ_OPT (encoding, "EUC-KR", 'E', 'U', 'C', '-', 'K', 'R', 0, 0, 0)
      || STREQ_OPT (encoding, "CP949", 'C', 'P', '9', '4', '9', 0, 0, 0, 0)
      || STREQ_OPT (encoding, "JOHAB", 'J', 'O', 'H', 'A', 'B', 0, 0, 0, 0))
    return 1;
  return 0;
}