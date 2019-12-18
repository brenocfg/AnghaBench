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
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int /*<<< orphan*/  test_EC_P256_carry_inner (int /*<<< orphan*/  const*,char*,char*) ; 

__attribute__((used)) static void
test_EC_P256_carry(const br_ec_impl *impl)
{
	test_EC_P256_carry_inner(impl,
		"0435BAA24B2B6E1B3C88E22A383BD88CC4B9A3166E7BCF94FF6591663AE066B33B821EBA1B4FC8EA609A87EB9A9C9A1CCD5C9F42FA1365306F64D7CAA718B8C978",
		"0447752A76CA890328D34E675C4971EC629132D1FC4863EDB61219B72C4E58DC5E9D51E7B293488CFD913C3CF20E438BB65C2BA66A7D09EABB45B55E804260C5EB");
	test_EC_P256_carry_inner(impl,
		"04DCAE9D9CE211223602024A6933BD42F77B6BF4EAB9C8915F058C149419FADD2CC9FC0707B270A1B5362BA4D249AFC8AC3DA1EFCA8270176EEACA525B49EE19E6",
		"048DAC7B0BE9B3206FCE8B24B6B4AEB122F2A67D13E536B390B6585CA193427E63F222388B5F51D744D6F5D47536D89EEEC89552BCB269E7828019C4410DFE980A");
}