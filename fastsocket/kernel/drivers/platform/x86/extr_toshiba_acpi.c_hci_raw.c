#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; TYPE_3__* elements; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
union acpi_object {TYPE_4__ package; TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int length; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  out_objs ;
typedef  scalar_t__ acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {TYPE_2__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_OK ; 
 int HCI_WORDS ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ *,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 scalar_t__ method_hci ; 

__attribute__((used)) static acpi_status hci_raw(const u32 in[HCI_WORDS], u32 out[HCI_WORDS])
{
	struct acpi_object_list params;
	union acpi_object in_objs[HCI_WORDS];
	struct acpi_buffer results;
	union acpi_object out_objs[HCI_WORDS + 1];
	acpi_status status;
	int i;

	params.count = HCI_WORDS;
	params.pointer = in_objs;
	for (i = 0; i < HCI_WORDS; ++i) {
		in_objs[i].type = ACPI_TYPE_INTEGER;
		in_objs[i].integer.value = in[i];
	}

	results.length = sizeof(out_objs);
	results.pointer = out_objs;

	status = acpi_evaluate_object(NULL, (char *)method_hci, &params,
				      &results);
	if ((status == AE_OK) && (out_objs->package.count <= HCI_WORDS)) {
		for (i = 0; i < out_objs->package.count; ++i) {
			out[i] = out_objs->package.elements[i].integer.value;
		}
	}

	return status;
}