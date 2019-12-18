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
struct resource {int dummy; } ;
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int checksum (struct pcmcia_socket*,struct resource*) ; 
 struct resource* claim_region (struct pcmcia_socket*,unsigned long,unsigned long,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_region (struct resource*) ; 

__attribute__((used)) static int
checksum_match(struct pcmcia_socket *s, unsigned long base, unsigned long size)
{
	struct resource *res1, *res2;
	int a = -1, b = -1;

	res1 = claim_region(s, base, size/2, IORESOURCE_MEM, "cs memory probe");
	res2 = claim_region(s, base + size/2, size/2, IORESOURCE_MEM, "cs memory probe");

	if (res1 && res2) {
		a = checksum(s, res1);
		b = checksum(s, res2);
	}

	free_region(res2);
	free_region(res1);

	return (a == b) && (a >= 0);
}