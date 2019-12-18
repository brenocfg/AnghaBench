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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AML_LEQUAL_OP ; 
 int /*<<< orphan*/  AML_LGREATER_OP ; 
 int /*<<< orphan*/  AML_LLESS_OP ; 
 int /*<<< orphan*/  FALSE ; 
#define  MATCH_MEQ 133 
#define  MATCH_MGE 132 
#define  MATCH_MGT 131 
#define  MATCH_MLE 130 
#define  MATCH_MLT 129 
#define  MATCH_MTR 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ex_do_logical_op (int /*<<< orphan*/ ,union acpi_operand_object*,union acpi_operand_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8
acpi_ex_do_match(u32 match_op,
		 union acpi_operand_object *package_obj,
		 union acpi_operand_object *match_obj)
{
	u8 logical_result = TRUE;
	acpi_status status;

	/*
	 * Note: Since the package_obj/match_obj ordering is opposite to that of
	 * the standard logical operators, we have to reverse them when we call
	 * do_logical_op in order to make the implicit conversion rules work
	 * correctly. However, this means we have to flip the entire equation
	 * also. A bit ugly perhaps, but overall, better than fussing the
	 * parameters around at runtime, over and over again.
	 *
	 * Below, P[i] refers to the package element, M refers to the Match object.
	 */
	switch (match_op) {
	case MATCH_MTR:

		/* Always true */

		break;

	case MATCH_MEQ:

		/*
		 * True if equal: (P[i] == M)
		 * Change to:     (M == P[i])
		 */
		status =
		    acpi_ex_do_logical_op(AML_LEQUAL_OP, match_obj, package_obj,
					  &logical_result);
		if (ACPI_FAILURE(status)) {
			return (FALSE);
		}
		break;

	case MATCH_MLE:

		/*
		 * True if less than or equal: (P[i] <= M) (P[i] not_greater than M)
		 * Change to:                  (M >= P[i]) (M not_less than P[i])
		 */
		status =
		    acpi_ex_do_logical_op(AML_LLESS_OP, match_obj, package_obj,
					  &logical_result);
		if (ACPI_FAILURE(status)) {
			return (FALSE);
		}
		logical_result = (u8) ! logical_result;
		break;

	case MATCH_MLT:

		/*
		 * True if less than: (P[i] < M)
		 * Change to:         (M > P[i])
		 */
		status =
		    acpi_ex_do_logical_op(AML_LGREATER_OP, match_obj,
					  package_obj, &logical_result);
		if (ACPI_FAILURE(status)) {
			return (FALSE);
		}
		break;

	case MATCH_MGE:

		/*
		 * True if greater than or equal: (P[i] >= M) (P[i] not_less than M)
		 * Change to:                     (M <= P[i]) (M not_greater than P[i])
		 */
		status =
		    acpi_ex_do_logical_op(AML_LGREATER_OP, match_obj,
					  package_obj, &logical_result);
		if (ACPI_FAILURE(status)) {
			return (FALSE);
		}
		logical_result = (u8) ! logical_result;
		break;

	case MATCH_MGT:

		/*
		 * True if greater than: (P[i] > M)
		 * Change to:            (M < P[i])
		 */
		status =
		    acpi_ex_do_logical_op(AML_LLESS_OP, match_obj, package_obj,
					  &logical_result);
		if (ACPI_FAILURE(status)) {
			return (FALSE);
		}
		break;

	default:

		/* Undefined */

		return (FALSE);
	}

	return logical_result;
}