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
struct TYPE_3__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_IA5STRING ;

/* Variables and functions */
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *ia5string(ASN1_IA5STRING *ia5)
{
  char *tmp;
  if(!ia5 || !ia5->length)
    return NULL;
  tmp = OPENSSL_malloc(ia5->length + 1);
  memcpy(tmp, ia5->data, ia5->length);
  tmp[ia5->length] = 0;
  return tmp;
}