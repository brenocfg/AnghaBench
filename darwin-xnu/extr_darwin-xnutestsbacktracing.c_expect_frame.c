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
typedef  int /*<<< orphan*/  CSSymbolRef ;

/* Variables and functions */
 scalar_t__ CSIsNull (int /*<<< orphan*/ ) ; 
 char* CSSymbolGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_EXPECT_EQ_STR (char const*,char const*,char*,unsigned int,char const*,char const*) ; 
 int /*<<< orphan*/  T_FAIL (char*,...) ; 
 int /*<<< orphan*/  T_LOG (char*,unsigned int) ; 
 int /*<<< orphan*/  T_QUIET ; 

__attribute__((used)) static void
expect_frame(const char **bt, unsigned int bt_len, CSSymbolRef symbol,
    unsigned long addr, unsigned int bt_idx, unsigned int max_frames)
{
    const char *name;
    unsigned int frame_idx = max_frames - bt_idx - 1;

    if (bt[frame_idx] == NULL) {
        T_LOG("frame %2u: skipping system frame", frame_idx);
        return;
    }

    if (CSIsNull(symbol)) {
        T_FAIL("invalid symbol for address %#lx at frame %d", addr, frame_idx);
        return;
    }

    if (frame_idx >= bt_len) {
        T_FAIL("unexpected frame '%s' (%#lx) at index %u",
            CSSymbolGetName(symbol), addr, frame_idx);
        return;
    }

    name = CSSymbolGetName(symbol);
    T_QUIET; T_ASSERT_NOTNULL(name, NULL);
    T_EXPECT_EQ_STR(name, bt[frame_idx],
        "frame %2u: saw '%s', expected '%s'",
        frame_idx, name, bt[frame_idx]);
}