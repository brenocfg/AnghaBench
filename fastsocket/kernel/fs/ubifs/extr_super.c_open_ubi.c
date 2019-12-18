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
struct ubi_volume_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ubi_volume_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char const) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 struct ubi_volume_desc* ubi_open_volume (int,int,int) ; 
 struct ubi_volume_desc* ubi_open_volume_nm (int,char const*,int) ; 

__attribute__((used)) static struct ubi_volume_desc *open_ubi(const char *name, int mode)
{
	int dev, vol;
	char *endptr;

	if (name[0] != 'u' || name[1] != 'b' || name[2] != 'i')
		return ERR_PTR(-EINVAL);

	/* ubi:NAME method */
	if ((name[3] == ':' || name[3] == '!') && name[4] != '\0')
		return ubi_open_volume_nm(0, name + 4, mode);

	if (!isdigit(name[3]))
		return ERR_PTR(-EINVAL);

	dev = simple_strtoul(name + 3, &endptr, 0);

	/* ubiY method */
	if (*endptr == '\0')
		return ubi_open_volume(0, dev, mode);

	/* ubiX_Y method */
	if (*endptr == '_' && isdigit(endptr[1])) {
		vol = simple_strtoul(endptr + 1, &endptr, 0);
		if (*endptr != '\0')
			return ERR_PTR(-EINVAL);
		return ubi_open_volume(dev, vol, mode);
	}

	/* ubiX:NAME method */
	if ((*endptr == ':' || *endptr == '!') && endptr[1] != '\0')
		return ubi_open_volume_nm(dev, ++endptr, mode);

	return ERR_PTR(-EINVAL);
}