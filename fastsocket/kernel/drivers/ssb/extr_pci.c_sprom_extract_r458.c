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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_sprom {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G0 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G01 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G1 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G2 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G23 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G3 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID2G3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G0 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G01 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G1 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G2 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G23 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G3 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5G3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH0 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH01 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH1 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH2 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH23 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH3 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GH3_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL0 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL01 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL0_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL1 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL1_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL2 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL23 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL2_SHIFT ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL3 ; 
 int /*<<< orphan*/  SSB_SPROM4_TXPID5GL3_SHIFT ; 
 int /*<<< orphan*/ * txpid2g ; 
 int /*<<< orphan*/ * txpid5g ; 
 int /*<<< orphan*/ * txpid5gh ; 
 int /*<<< orphan*/ * txpid5gl ; 

__attribute__((used)) static void sprom_extract_r458(struct ssb_sprom *out, const u16 *in)
{
	SPEX(txpid2g[0], SSB_SPROM4_TXPID2G01,
	     SSB_SPROM4_TXPID2G0, SSB_SPROM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPROM4_TXPID2G01,
	     SSB_SPROM4_TXPID2G1, SSB_SPROM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPROM4_TXPID2G23,
	     SSB_SPROM4_TXPID2G2, SSB_SPROM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPROM4_TXPID2G23,
	     SSB_SPROM4_TXPID2G3, SSB_SPROM4_TXPID2G3_SHIFT);

	SPEX(txpid5gl[0], SSB_SPROM4_TXPID5GL01,
	     SSB_SPROM4_TXPID5GL0, SSB_SPROM4_TXPID5GL0_SHIFT);
	SPEX(txpid5gl[1], SSB_SPROM4_TXPID5GL01,
	     SSB_SPROM4_TXPID5GL1, SSB_SPROM4_TXPID5GL1_SHIFT);
	SPEX(txpid5gl[2], SSB_SPROM4_TXPID5GL23,
	     SSB_SPROM4_TXPID5GL2, SSB_SPROM4_TXPID5GL2_SHIFT);
	SPEX(txpid5gl[3], SSB_SPROM4_TXPID5GL23,
	     SSB_SPROM4_TXPID5GL3, SSB_SPROM4_TXPID5GL3_SHIFT);

	SPEX(txpid5g[0], SSB_SPROM4_TXPID5G01,
	     SSB_SPROM4_TXPID5G0, SSB_SPROM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPROM4_TXPID5G01,
	     SSB_SPROM4_TXPID5G1, SSB_SPROM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPROM4_TXPID5G23,
	     SSB_SPROM4_TXPID5G2, SSB_SPROM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPROM4_TXPID5G23,
	     SSB_SPROM4_TXPID5G3, SSB_SPROM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPROM4_TXPID5GH01,
	     SSB_SPROM4_TXPID5GH0, SSB_SPROM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPROM4_TXPID5GH01,
	     SSB_SPROM4_TXPID5GH1, SSB_SPROM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPROM4_TXPID5GH23,
	     SSB_SPROM4_TXPID5GH2, SSB_SPROM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPROM4_TXPID5GH23,
	     SSB_SPROM4_TXPID5GH3, SSB_SPROM4_TXPID5GH3_SHIFT);
}