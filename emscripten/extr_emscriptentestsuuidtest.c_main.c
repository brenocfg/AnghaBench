#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ uuid_t ;

/* Variables and functions */
 scalar_t__ UUID_TYPE_DCE_RANDOM ; 
 scalar_t__ UUID_VARIANT_DCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int isUUID (char*,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  uuid_clear (TYPE_1__) ; 
 scalar_t__ uuid_compare (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  uuid_copy (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  uuid_generate (TYPE_1__) ; 
 int uuid_is_null (TYPE_1__) ; 
 scalar_t__ uuid_parse (char*,TYPE_1__) ; 
 scalar_t__ uuid_type (TYPE_1__) ; 
 int /*<<< orphan*/  uuid_unparse (TYPE_1__,char*) ; 
 int /*<<< orphan*/  uuid_unparse_lower (TYPE_1__,char*) ; 
 int /*<<< orphan*/  uuid_unparse_upper (TYPE_1__,char*) ; 
 scalar_t__ uuid_variant (TYPE_1__) ; 

int main() {
    uuid_t uuid;
    uuid_t uuid1;
    uuid_t uuid2;
    uuid_t empty_uuid = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uuid_generate(uuid);

    assert(uuid_is_null(uuid) == 0);
    assert(uuid_type(uuid) == UUID_TYPE_DCE_RANDOM);
    assert(uuid_variant(uuid) == UUID_VARIANT_DCE);

    char *generated = (char *)malloc(37*sizeof(char));
    uuid_unparse(uuid, generated);
    assert(isUUID(generated, 0) == 1); // Check it's a valid lower case UUID string.
    printf("\nuuid = %s\n", generated);

    assert(uuid_parse(generated, uuid1) == 0); // Check the generated UUID parses correctly into a compact UUID.
    assert(uuid_compare(uuid1, uuid) == 0);    // Compare the parsed UUID with the original.

    uuid_unparse_lower(uuid, generated);
    assert(isUUID(generated, 0) == 1); // Check it's a valid lower case UUID string.
    printf("uuid = %s\n", generated);

    uuid_unparse_upper(uuid, generated);
    assert(isUUID(generated, 1) == 1); // Check it's a valid upper case UUID string.
    printf("uuid = %s\n", generated);


    uuid_copy(uuid2, uuid);
    assert(uuid_compare(uuid2, uuid) == 0);

    uuid_clear(uuid);
    assert(uuid_compare(empty_uuid, uuid) == 0);

    assert(uuid_is_null(uuid) == 1);

    // The following lets the browser test exit cleanly.
#ifdef REPORT_RESULT
    REPORT_RESULT(1);
#endif
    exit(0);
}