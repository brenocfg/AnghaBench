int
dlg_ttysize(int fd, int *high, int *wide)
{
    int rc = -1;
#ifdef HAVE_SIZECHANGE
    if (isatty(fd)) {
	STRUCT_WINSIZE size;

	if (ioctl(fd, IOCTL_WINSIZE, &size) >= 0) {
	    *high = WINSIZE_ROWS(size);
	    *wide = WINSIZE_COLS(size);
	    rc = 0;
	}
    }
#else
    high = 24;
    wide = 80;
#endif /* HAVE_SIZECHANGE */
    return rc;
}